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
}
