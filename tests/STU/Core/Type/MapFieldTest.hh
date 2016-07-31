<?hh
namespace STU\Core\Type;

use STU\Model\MapTableInterface;
use \Mockery as m;

class MapFieldTest extends \PHPUnit_Framework_TestCase {

	public function setUp() {
		$this->map_field = m::mock(MapTableInterface::class);

		$this->type = new MapField($this->map_field);
	}

	public function testJsonSerializeReturnsCorrectDict() {
		$id = 666;
		$cx = 42;
		$cy = 21;
		$type_id = 88;
		$item_count = 77;

		$this->map_field->shouldReceive('getId')->once()->andReturn($id);
		$this->map_field->shouldReceive('getCx')->once()->andReturn($cx);
		$this->map_field->shouldReceive('getCy')->once()->andReturn($cy);
		$this->map_field->shouldReceive('getTypeId')->once()->andReturn($type_id);

		$this->type->setItemCount($item_count);

		$this->assertSame(
			[
				'id' => $id,
				'cx' => $cx,
				'cy' => $cy,
				'type_id' => $type_id,
				'item_count' => $item_count
			],
			$this->type->jsonSerialize()
		);
	}
}
