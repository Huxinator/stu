<?hh // strict
namespace STU\Core\Map;

use STU\Model\MapTableInterface;
use STU\Core\Ship\LongRangeScannerInterface;

class ComponentFactory implements ComponentFactoryInterface {

	public function __construct(private MapTableInterface $map): void {
	}

	public function createFieldsAroundPoint(int $cx, int $cy, LongRangeScannerInterface $scanner): FieldsAroundPointInterface {
		return new FieldsAroundPoint($this->map, $cx, $cy, $scanner);
	}
}
