<?hh
namespace STU\Core\Ship;

use Mockery as m;
use STU\Model\ShipTableInterface;

class ShortRangeScannerTest extends \PHPUnit_Framework_TestCase {

	public function setUp() {
		$this->ship = m::mock(ShipTableInterface::class);

		$this->scanner = new ShortRangeScanner($this->ship);
	}

	public function testGetEnergyConsumptionReturnsDemoValue() {
		$this->assertSame(
			1,
			$this->scanner->getEnergyConsumption()
		);
	}

	public function testGetShipListReturnsVector() {
		$id = 1414;
		$cx = 666;
		$cy = 42;
		$map_instance_id = 123;
		$result = Vector{};

		$query = sprintf('id != %d and map_instance_id = %d and cx = %d and cy = %d', $id, $map_instance_id, $cx, $cy);

		$this->ship->shouldReceive('getId')->once()->andReturn($id);
		$this->ship->shouldReceive('getCx')->once()->andReturn($cx);
		$this->ship->shouldReceive('getCy')->once()->andReturn($cy);
		$this->ship->shouldReceive('getMapInstanceId')->once()->andReturn($map_instance_id);
		$this->ship->shouldReceive('getObjectsBy')->with($query)->once()->andReturn($result);

		$this->assertSame(
			$result,
			$this->scanner->getShipList()
		);
	}
}
