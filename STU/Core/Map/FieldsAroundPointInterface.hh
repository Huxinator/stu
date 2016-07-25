<?hh
namespace STU\Core\Map;

use STU\Model\MapTableInterface;

interface FieldsAroundPointInterface {

	public function getFieldsAsMatrix(): Map<int, Map<int, ?MapTableInterface>>;
}
