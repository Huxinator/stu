<?hh
namespace STU\Core\Ship;

use Mockery as m;
use STU\Model\ShipTableInterface;

class LongRangeScannerTest extends \PHPUnit_Framework_TestCase {

	public function setUp() {
		$this->ship = m::mock(ShipTableInterface::class);

		$this->scanner = new LongRangeScanner($this->ship);
	}

	public function testGetEnergyConsumptionReturnsDemoValue() {
		$this->assertSame(
			1,
			$this->scanner->getEnergyConsumption()
		);
	}

	public function testGetSensorRangeReturnsDemoValue() {
		$this->assertSame(
			1,
			$this->scanner->getSensorRange()
		);
	}
}
