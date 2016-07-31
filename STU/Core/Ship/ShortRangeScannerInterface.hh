<?hh // strict
namespace STU\Core\Ship;

use STU\Model\ShipTableInterface;

interface ShortRangeScannerInterface extends ShipSystemInterface {

	public function getShipList(): Vector<ShipTableInterface>;
}
