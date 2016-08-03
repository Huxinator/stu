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
			$user = $this->getDIContainer()->user;
			$result->add(
				new Type\ForeignShip(
					$foreign_ship,
					new Type\ForeignUser($user->getById($foreign_ship->getUserId()))
				)
			);
		}
		return $result;
	}

	public function getStorage(int $ship_id): Type\ShipStorageInterface {
		$ship = $this->getShip($ship_id);
		$ship_storage = $this->getDIContainer()->ship_storage;

		return new Type\ShipStorage(
			$ship_storage->getObjectsBy(
				sprintf('ship_id = %d', $ship->getId()),
				'commodity_id ASC'
			)
		);
	}

	/**
	 * @todo Move into own handler
	 * @todo Add energy consumption
	 */
	public function beamToShip(int $ship_id, int $foreign_ship_id, array<int,\stdClass> $commodity_list): void {
		$ship = $this->getShip($ship_id);
		$foreign_ship = $this->getDIContainer()->ship->findObject('id='.$foreign_ship_id);

		if ($foreign_ship->getMapInstanceId() != $ship->getMapInstanceId()) {
			throw new \Exception('Wrong mapfield');
		}
		if ($foreign_ship->getCx() != $ship->getCx() || $foreign_ship->getCy() != $ship->getCy()) {
			throw new \Exception('Wrong mapfield');
		}
		$ship_storage = $this->getDIContainer()->ship_storage->getObjectsBy(
			sprintf('ship_id = %d', $ship->getId())
		);

		$commodities_to_beam = Map{};
		foreach ($commodity_list as $entry) {
			$vars = get_object_vars($entry);
			if ($vars === null || !array_key_exists('commodity_id', $vars) || !array_key_exists('amount', $vars)) {
				continue;
			}
			$commodities_to_beam[(int) $vars['commodity_id']] = $vars['amount'];
		}
		foreach ($ship_storage as $storage_item) {
			$commodity_id = $storage_item->getCommodityId();
			if (!$commodities_to_beam->contains($commodity_id)) {
				continue;
			}
			$amount = min($storage_item->getAmount(), $commodities_to_beam->get($commodity_id));
			try {
				$foreign_storage_item = $this->getDIContainer()->ship_storage->findObject(
					sprintf(
						'ship_id = %d AND commodity_id = %d', $foreign_ship->getId(), $commodity_id
					)
				);
			} catch (\Exception $e) {
				$foreign_storage_item = $this->getDIContainer()->ship_storage;
				$foreign_storage_item->setCommodityId($commodity_id);
				$foreign_storage_item->setShipId($foreign_ship->getId());
			}
			$foreign_storage_item->setAmount(
				$foreign_storage_item->getAmount() + $amount
			);
			$foreign_storage_item->save();

			if ($storage_item->getAmount() == $amount) {
				$storage_item->delete();
			} else {
				$storage_item->setAmount(
					$storage_item->getAmount() - $amount
				);
				$storage_item->save();
			}
		}
		return;
	}
}
