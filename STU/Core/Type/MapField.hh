<?hh
namespace STU\Core\Type;

use STU\Model\MapTableInterface;

class MapField implements \JsonSerializable {

	public function __construct(private ?MapTableInterface $map_field): void {
	}

	public function jsonSerialize(): ?\stdClass {
		$map_field = $this->map_field;
		if ($map_field === null) {
			return null;
		}
		$field = new \stdClass();
		$field->id = $map_field->getId();
		$field->cx = $map_field->getCx();
		$field->cy = $map_field->getCy();
		$field->type_id = $map_field->getTypeId();

		return $field;
	}
}
