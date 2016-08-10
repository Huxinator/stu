<?hh // strict
namespace STU\Core\Type;

use STU\Model\PlanetTableInterface;

final class PlanetListItem implements PlanetListItemInterface {

	public function __construct(private PlanetTableInterface $planet): void {
	}   

	public function jsonSerialize(): Map<string,mixed> {
		return new Map([
			'id' => $this->planet->getId(),
			'name' => $this->planet->getName()
		]);
	}   
}
