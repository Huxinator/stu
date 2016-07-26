<?hh // strict
namespace STU\Core\Ship;

class LongRangeScanner implements LongRangeScannerInterface {

	public function __construct(private \STU\Model\ShipTableInterface $ship): void {}
	
	/**
	 * @todo
	 */
	public function getSensorRange(): int {
		return 1;
	}
}
