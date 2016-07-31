<?hh // strict
namespace STU\Core\RPC;

use STU\Core\Type;
use STU\Model\ShipTableInterface;
use STU\Model\UserTable;

final class Ship extends Base {

	const int ERROR_SHIELD_NOT_LOADED = 1;
	const int ERROR_NOT_ENOUGH_POWER = 2;
	const int ERROR_NOT_ALLOWED = 3;
	const int ERROR_SYSTEM_NOT_ACTIVATED = 4;

	public function __construct(\STU\DI\DIContainer $di, private \STU\Core\Ship\ComponentFactoryInterface $component_factory) {
		parent::__construct($di);
	}

	private function getShip(int $ship_id): ShipTableInterface {
		$ship = $this->getDIContainer()->ship->findObject('id='.$ship_id);

		$user = $this->getSessionManager()->getCurrentUser();

		if (
			!$ship || 
			$ship->getUserId() != $user->getId()
		) {
			$this->fault('Ship not found', self::OBJECT_NOT_FOUND);
		}

		return $ship;
	}

	public function getDetails(int $ship_id): Type\Ship {
		$ship = $this->getShip($ship_id);

		return new Type\Ship($ship);
	}

	public function activateShield(int $ship_id): Type\Ship {
		$ship = $this->getShip($ship_id);
		
		if ($ship->getShields() == 0) {
			$this->fault('Die Schilde sind nicht aufgeladen', self::ERROR_SHIELD_NOT_LOADED);
		}
		if ($ship->getEnergy() < 1) {
			$this->fault('Es wird 1 Energie benötigt', self::ERROR_NOT_ENOUGH_POWER);
		}
		$ship->setEnergy($ship->getEnergy() - 1);
		$ship->setShieldActive(1);
		$ship->save();

		return new Type\Ship($ship);
	}
	
	public function deActivateShield(int $ship_id): Type\Ship {
		$ship = $this->getShip($ship_id);
		
		$ship->setShieldActive(0);
		$ship->save();
		
		return new Type\Ship($ship);
	}

	public function getMap(int $ship_id): array<array<Type\MapField>> {
		$ship = $this->getShip($ship_id);
		if ($ship->getLrsActive() == 0) {
			$this->fault('Die Langstreckensensoren sind nicht aktiviert', static::ERROR_NOT_ALLOWED);
		}

		$fields = $this->getDIContainer()->map_component_factory->createFieldsAroundPoint(
			$ship->getMapInstanceId(),
			$ship->getCx(),
			$ship->getCy(),
			$this->component_factory->createLongRangeScanner($ship)
		);

		return array_map(function ($item) use ($ship) {
				return array_map(function ($field) use ($ship) {
					if ($field === null) {
						return null;
					}
					/**
					 * @todo For now its ok to retrieve
					 * the item count on a per-field
					 * basis. But having a n*n amount of
					 * queries is no solution for the
					 * future
					 */
					$mapfield = new Type\MapField($field);
					$mapfield->setItemCount(
						$ship->count(
							sprintf(
								'id != %d and map_instance_id = %d and cx = %d AND cy = %d',
								$ship->getId(),
								$ship->getMapInstanceId(),
								$field->getCx(),
								$field->getCy()
							)
						)
					);
					return $mapfield;
				},
				$item);
			},
			$fields->getFieldsAsMatrix()
		);
	}

	public function move(int $ship_id, int $field_id): Type\MoveResult {
		$move = $this->component_factory->createMove($this->getShip($ship_id));
		$map_field = $this->getDIContainer()->map->getById($field_id);

		return $move->toField($map_field);
	}

	public function toggleLongRangeScanner(int $ship_id): Type\Ship {
		$ship = $this->getShip($ship_id);
		if ($ship->getLrsActive() == 0) {
			$scanner = $this->component_factory->createLongRangeScanner($ship);
			$energy_consumtion = $scanner->getEnergyConsumption();
			if ($ship->getEnergy() < $energy_consumtion) {
				$this->fault(
					sprintf('Es wird %d Energie benötigt', $energy_consumtion),
					self::ERROR_NOT_ENOUGH_POWER
				);
			}
			$ship->setEnergy($ship->getEnergy() - $energy_consumtion);
			$ship->setLrsActive(1);
		} else {
			$ship->setLrsActive(0);
		}
		
		$ship->save();
		
		return new Type\Ship($ship);
	}

	public function toggleShortRangeScanner(int $ship_id): Type\Ship {
		$ship = $this->getShip($ship_id);
		if ($ship->getSrsActive() == 0) {
			$scanner = $this->component_factory->createShortRangeScanner($ship);
			$energy_consumtion = $scanner->getEnergyConsumption();
			if ($ship->getEnergy() < $energy_consumtion) {
				$this->fault(
					sprintf('Es wird %d Energie benötigt', $energy_consumtion),
					self::ERROR_NOT_ENOUGH_POWER
				);
			}
			$ship->setEnergy($ship->getEnergy() - $energy_consumtion);
			$ship->setSrsActive(1);
		} else {
			$ship->setSrsActive(0);
		}
		
		$ship->save();
		
		return new Type\Ship($ship);
	}

	public function getShipListByShipPosition(int $ship_id): Vector<Type\ForeignShip> {
		$ship = $this->getShip($ship_id);
		if ($ship->getSrsActive() === 0) {
			$this->fault('Kurzstreckensensoren nicht aktiviert', static::ERROR_SYSTEM_NOT_ACTIVATED);
		}
		$scanner = $this->component_factory->createShortRangeScanner($ship);

		$result = Vector{};
		foreach ($scanner->getShipList() as $foreign_ship) {
			$result->add(
				new Type\ForeignShip($foreign_ship)
			);
		}
		return $result;
	}
}
