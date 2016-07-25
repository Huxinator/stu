<?hh //strict
namespace STU\Core\Map;

use STU\Core\Ship\LongRangeScannerInterface;

interface ComponentFactoryInterface {

	public function createFieldsAroundPoint(int $cx, int $cy, LongRangeScannerInterface $scanner): FieldsAroundPointInterface;
}
