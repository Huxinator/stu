<?hh
namespace STU\Core\Ship;

use STU\Model\ShipTableInterface;

class ComponentFactory implements ComponentFactoryInterface {
	
	public function createLongRangeScanner(ShipTableInterface $ship): LongRangeScannerInterface {
		return new LongRangeScanner($ship);
	}

	public function createMove(ShipTableInterface $ship): MoveInterface {
		return new Move($ship);
	}
}
