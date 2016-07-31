<?hh
namespace STU\Core\Ship;

use STU\Model\ShipTableInterface;
use Mockery as m;

class ComponentFactoryTest extends \PHPUnit_Framework_TestCase {

	public function setUp() {
		$this->ship = m::mock(ShipTableInterface::class);

		$this->scanner = new ComponentFactory();
	}

	public function testCreateLongRangeScannerReturnsInstance() {
		$this->assertInstanceOf(
			LongRangeScannerInterface::class,
			$this->scanner->createLongRangeScanner($this->ship)
		);
	}

	public function testCreateShortRangeScannerReturnsInstance() {
		$this->assertInstanceOf(
			ShortRangeScannerInterface::class,
			$this->scanner->createShortRangeScanner($this->ship)
		);
	}

	public function testCreateMoveReturnsInstance() {
		$this->assertInstanceOf(
			MoveInterface::class,
			$this->scanner->createMove($this->ship)
		);
	}
}
