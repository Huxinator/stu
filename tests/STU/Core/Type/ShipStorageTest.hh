<?hh
namespace STU\Core\Type;

use STU\Model\ShipStorageTableInterface;
use Mockery as m;

class ShipStorageTest extends \PHPUnit_Framework_TestCase {

	public function setUp() {
		$this->storage = m::mock(ShipStorageTableInterface::class);

		$this->type = new ShipStorage(new Vector([$this->storage]));
	}

	public function testJsonSerializeReturnsCorrectDict() {
		$commodity_id = 1234;
		$amount = 5678;

		$this->storage->shouldReceive('getCommodityId')->once()->andReturn($commodity_id);
		$this->storage->shouldReceive('getAmount')->once()->andReturn($amount);

		$this->assertSame(
			[
				[
					'commodity_id' => $commodity_id,
					'amount' => $amount
				]
			],
			$this->type->jsonSerialize()
		);
	}
}
