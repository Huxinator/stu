<?hh // strict
namespace STU\Core\Ship;

final class LongRangeScanner implements LongRangeScannerInterface, ShipSystemInterface {

	public function __construct(private \STU\Model\ShipTableInterface $ship): void {}
	
	/**
	 * @todo
	 */
	public function getSensorRange(): int {
		return 1;
	}

	/**
	 * Energy cost during tick and activation
	 *
	 * @todo
	 */
	public function getEnergyConsumption(): int {
		return 1;
	}
}
