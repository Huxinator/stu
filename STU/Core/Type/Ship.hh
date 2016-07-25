<?hh
namespace STU\Core\Type;

use \STU\Model\ShipTableInterface;

class Ship implements \JsonSerializable {

	public function __construct(private ShipTableInterface $ship): void {
	}
	
	public function jsonSerialize(): \stdClass {
		$ship_json = new \stdClass();
		$ship_json->id = $this->ship->getId();
		$ship_json->name = $this->ship->getName();
		$ship_json->hull = $this->ship->getHull();
		$ship_json->type_id = 1;
		$ship_json->cx = $this->ship->getCx();
		$ship_json->cy = $this->ship->getCy();
		$ship_json->sector = $this->ship->getCx().'/'.$this->ship->getCy();
		$ship_json->energy = $this->ship->getEnergy();
		$ship_json->shield = $this->ship->getShields();
		$ship_json->shield_active = $this->ship->getShieldActive();

		return $ship_json;
	}
}
