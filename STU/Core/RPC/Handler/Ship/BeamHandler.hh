<?hh // strict
namespace STU\Core\RPC\Handler\Ship;

use STU\Model\ShipStorageTableInterface;
use STU\Model\ShipTableInterface;

final class BeamHandler implements BeamHandlerInterface {

	public function __construct(private ShipStorageTableInterface $ship_storage) {
	}

	public function beam(ShipTableInterface $ship, ShipTableInterface $foreign_ship, array<int,\stdClass> $commodity_list): array<int,int> {
		$this->performMapFieldCheck($ship, $foreign_ship);
		$foreign_ship_storage = $this->ship_storage->getObjectsBy(
			sprintf('ship_id = %d', $foreign_ship->getId())
		);

		$commodities_to_beam = $this->rebuildCommodityList($commodity_list);
		$result = [];
		foreach ($foreign_ship_storage as $foreign_storage_item) {
			$commodity_id = $foreign_storage_item->getCommodityId();
			if (!$commodities_to_beam->contains($commodity_id)) {
				continue;
			}
			$amount = min($foreign_storage_item->getAmount(), $commodities_to_beam->get($commodity_id));

			$this->raiseStorage($ship, $commodity_id, $amount);
			$this->lowerStorage($foreign_storage_item, $amount);

			$result[$commodity_id] = $amount;
		}
		return $result;
	}

	private function raiseStorage(ShipTableInterface $ship, int $commodity_id, int $amount): void {
		try {
			$storage_item = $this->ship_storage->findObject(
				sprintf(
					'ship_id = %d AND commodity_id = %d', $ship->getId(), $commodity_id
				)
			);
		} catch (\Exception $e) {
			$storage_item = $this->createNewStorageitem($ship, $commodity_id);
		}
		$storage_item->setAmount(
			$storage_item->getAmount() + $amount
		);
		$storage_item->save();
	}

	private function lowerStorage(ShipStorageTableInterface $storage_item, int $amount): void {
		if ($storage_item->getAmount() == $amount) {
			$storage_item->delete();
		} else {
			$storage_item->setAmount(
				$storage_item->getAmount() - $amount
			);
			$storage_item->save();
		}
	}

	private function createNewStorageitem(ShipTableInterface $ship, int $commodity_id): ShipStorageTableInterface {
		$storage_item = clone $this->ship_storage;
		$storage_item->setCommodityId($commodity_id);
		$storage_item->setShipId($ship->getId());
		return $storage_item;
	}

	private function performMapFieldCheck(ShipTableInterface $ship, ShipTableInterface $foreign_ship): void {
		if ($foreign_ship->getMapInstanceId() != $ship->getMapInstanceId()) {
			throw new \Exception('Wrong mapfield');
		}
		if ($foreign_ship->getCx() != $ship->getCx() || $foreign_ship->getCy() != $ship->getCy()) {
			throw new \Exception('Wrong mapfield');
		}
	}

	private function rebuildCommodityList(array<int,\stdClass> $commodity_list): Map<int,int> {
		$commodities_to_beam = Map{};
		foreach ($commodity_list as $entry) {
			$vars = get_object_vars($entry);
			if ($vars === null || !array_key_exists('commodity_id', $vars) || !array_key_exists('amount', $vars)) {
				continue;
			}
			$commodities_to_beam[(int) $vars['commodity_id']] = $vars['amount'];
		}
		return $commodities_to_beam;
	}
}
