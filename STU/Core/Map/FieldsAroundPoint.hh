<?hh // strict
namespace STU\Core\Map;

use STU\Core\Ship\LongRangeScannerInterface;
use STU\Model\MapTableInterface;

class FieldsAroundPoint implements FieldsAroundPointInterface {

	public function __construct(
		private MapTableInterface $map,
		private int $instance_id,
		private int $cx,
		private int $cy,
		private LongRangeScannerInterface $scanner
	): void {
	}

	public function getFieldsAsMatrix(): Map<int, Map<int, ?MapTableInterface>> {
		$range = $this->scanner->getSensorRange();
		$startx = $this->cx - $range;
		$starty = $this->cy - $range;
		$endx = $this->cx + $range;
		$endy = $this->cy + $range;

		$matrix = Map{};
		for ($i = $starty; $i <= $endy; $i++) {
			$matrix[$i] = new Map(array_fill_keys(range($startx, $endx), null));

		}
		$fields = $this->map->getObjectsBy(
				sprintf(
					'instance_id = %d AND cx BETWEEN %d AND %d AND cy BETWEEN %d AND %d',
					$this->instance_id,
					$this->cx - $range,
					$this->cx + $range,
					$this->cy - $range,
					$this->cy + $range
				),
				'cy, cx'
			);
		foreach ($fields as $field) {
			$matrix[$field->getCy()][$field->getCx()] = $field;
		}

		return $matrix;
	}
}
