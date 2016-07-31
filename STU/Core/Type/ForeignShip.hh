<?hh // strict
namespace STU\Core\Type;

use STU\Model\ShipTableInterface;

/**
 * Class: ForeignShip
 *
 * @see \JsonSerializable
 * @final
 *
 * Foreign ships are ships which are not owned by the user. So we dont provide
 * critical information about the ships state like energy, hitpoints, etc
 */
final class ForeignShip implements \JsonSerializable {

	public function __construct(private ShipTableInterface $ship): void {
	}
	
	/**
	 * @todo return hull and shield values as percentages
	 */
	public function jsonSerialize(): array<string, mixed> {
		return [
			'id' => $this->ship->getId(),
			'name' => $this->ship->getName(),
			'type_id' => 1,
			'cx' => $this->ship->getCx(),
			'cy' => $this->ship->getCy(),
			'shield_active' => $this->ship->getShieldActive(),
		];
	}
}
