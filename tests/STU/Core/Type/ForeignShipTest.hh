<?hh
namespace STU\Core\Type;

use STU\Model\ShipTableInterface;
use Mockery as m;

class ForeignShipTest extends \PHPUnit_Framework_TestCase {

	public function setUp() {
		$this->ship = m::mock(ShipTableInterface::class);
		$this->user = m::mock(ForeignUserInterface::class);

		$this->type = new ForeignShip($this->ship, $this->user);
	}

	public function testJsonSerializeReturnsCorrectDict() {
		$id = 42;
		$name = 'my-fancy-ship';
		$type_id = 1;
		$cx = 666;
		$cy = 999;
		$shield_active = 1;

		$this->ship->shouldReceive('getId')->once()->andReturn($id);
		$this->ship->shouldReceive('getName')->once()->andReturn($name);
		$this->ship->shouldReceive('getCx')->once()->andReturn($cx);
		$this->ship->shouldReceive('getCy')->once()->andReturn($cy);
		$this->ship->shouldReceive('getShieldActive')->once()->andReturn($shield_active);
		
		$this->assertSame(
			[
				'id' => $id,
				'name' => $name,
				'type_id' => $type_id,
				'cx' => $cx,
				'cy' => $cy,
				'shield_active' => $shield_active,
				'user' => $this->user
			],
			$this->type->jsonSerialize()
		);
	}
}
