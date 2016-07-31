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
}
