<?hh // strict
namespace STU\Core\Ship;

interface LongRangeScannerInterface extends ShipSystemInterface {

	public function getSensorRange(): int;
}
