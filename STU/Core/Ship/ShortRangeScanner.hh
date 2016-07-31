<?hh // strict
namespace STU\Core\Ship;

use STU\Model\ShipTableInterface;

final class ShortRangeScanner implements ShortRangeScannerInterface {

	public function __construct(private ShipTableInterface $ship): void {
	}

	/**
	 * Energy cost during tick and activation
	 *
	 * @todo
	 */
	public function getEnergyConsumption(): int {
		return 1;
	}

	/**
	 * @todo sorting?
	 */
	public function getShipList(): Vector<ShipTableInterface> {
		return $this->ship->getObjectsBy(
			sprintf(
				'id != %s and map_instance_id = %d and cx = %d and cy = %d',
				$this->ship->getId(),
				$this->ship->getMapInstanceId(),
				$this->ship->getCx(),
				$this->ship->getCy()
			)
		);
	}
}
