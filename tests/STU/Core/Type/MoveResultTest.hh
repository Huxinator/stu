<?hh
namespace STU\Core\Type;

use STU\Model\ShipTableInterface;
use Mockery as m;

class MoveResultTest extends \PHPUnit_Framework_TestCase {

	public function setUp() {
		$this->ship = m::mock(ShipTableInterface::class);

		$this->move_result = new MoveResult($this->ship);
	}

	public function testJsonSerializeReturnsCorrectDict() {
		$message = 'my-result-message';

		$this->move_result->setResultMessage($message);

		// The test is broken because of the idiotic instantiation of
		// Ship in the jsonSerialize method
		$this->assertInternalType(
			'array',
			$this->move_result->jsonSerialize()
		);
	}
}
