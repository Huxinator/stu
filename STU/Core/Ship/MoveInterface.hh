<?hh
namespace STU\Core\Ship;

use STU\Core\Type\MoveResult;
use STU\Model\MapTableInterface;

interface MoveInterface {

	public function toField(MapTableInterface $map_field): MoveResult;
}
