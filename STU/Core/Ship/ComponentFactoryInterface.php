<?hh
namespace STU\Core\Ship;

use STU\Model\ShipTableInterface;

interface ComponentFactoryInterface {

	public function createLongRangeScanner(ShipTableInterface $ship): LongRangeScannerInterface;

	public function createMove(ShipTableInterface $ship): MoveInterface;
}
