<?hh // strict
namespace STU\Core\Type;

use STU\Model\ShipTableInterface;

class Ship implements \JsonSerializable {

	public function __construct(private ShipTableInterface $ship): void {
	}
	
	public function jsonSerialize(): array<string, mixed> {
		// `sector` is deprecated, the client should handle this
		return [
			'id' => $this->ship->getId(),
			'name' => $this->ship->getName(),
			'hull' => $this->ship->getHull(),
			'type_id' => 1,
			'cx' => $this->ship->getCx(),
			'cy' => $this->ship->getCy(),
			'sector' => sprintf('%d/%d', $this->ship->getCx(), $this->ship->getCy()),
			'energy' => $this->ship->getEnergy(),
			'shield' => $this->ship->getShields(),
			'shield_active' => $this->ship->getShieldActive()
		];
	}
}
