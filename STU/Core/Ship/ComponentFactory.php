<?hh // strict
namespace STU\Core\Ship;

use STU\Model\ShipTableInterface;

final class ComponentFactory implements ComponentFactoryInterface {
	
	public function createLongRangeScanner(ShipTableInterface $ship): LongRangeScannerInterface {
		return new LongRangeScanner($ship);
	}

	public function createShortRangeScanner(ShipTableInterface $ship): ShortRangeScannerInterface {
		return new ShortRangeScanner($ship);
	}

	public function createMove(ShipTableInterface $ship): MoveInterface {
		return new Move($ship);
	}
}
