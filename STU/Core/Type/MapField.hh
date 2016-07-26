<?hh // strict
namespace STU\Core\Type;

use STU\Model\MapTableInterface;

class MapField implements \JsonSerializable {

	public function __construct(private MapTableInterface $map_field): void {
	}

	public function jsonSerialize(): array<string, mixed> {
		return [
			'id' => $this->map_field->getId(),
			'cx' => $this->map_field->getCx(),
			'cy' => $this->map_field->getCy(),
			'type_id' => $this->map_field->getTypeId()
		];
	}
}
