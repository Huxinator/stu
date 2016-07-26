<?hh // strict
namespace STU\Core\Ship;

use STU\Model\ShipTableInterface;
use STU\Model\MapTableInterface;
use STU\Core\Type\MoveResult;

class Move implements MoveInterface {

	public function __construct(private ShipTableInterface $ship): void {
	}

	public function toField(MapTableInterface $map_field): MoveResult {
		$result = new MoveResult($this->ship);
		if ($map_field->getCx() === $this->ship->getCx() &&
			$map_field->getCy() === $this->ship->getCy()) {
			throw new \Exception('1');
		}
		if ($map_field->getCx() !== $this->ship->getCx() &&
			$map_field->getCy() !== $this->ship->getCy()) {
			throw new \Exception('2');
		}
		$fields = $this->getMapFieldList($map_field);
		foreach ($fields as $field) {
			// @todo implement field effects
			$this->ship->setCx($map_field->getCx());
			$this->ship->setCy($map_field->getCy());
			$this->ship->save();
		}
		return $result;
	}

	private function getMapFieldList(MapTableInterface $map_field): Vector<MapTableInterface> {
		if ($map_field->getCx() == $this->ship->getCx()) {
			$query_parts = $this->calculateQueryParts(
				$this->ship->getCy(),
				$map_field->getCy()
			);
			$query = sprintf(
				'cx = %d AND cy BETWEEN %d AND %d',
				$map_field->getCx(),
				$query_parts['start'],
				$query_parts['end']
			);
			$order = 'cy '.(string) $query_parts['order'];
		} else {
			$query_parts = $this->calculateQueryParts(
				$this->ship->getCx(),
				$map_field->getCx()
			);
			$query = sprintf(
				'cy = %d AND cx BETWEEN %d AND %d',
				$map_field->getCy(),
				$query_parts['start'],
				$query_parts['end']
			);
			$order = 'cx '.(string) $query_parts['order'];
		}
		return new Vector($map_field->getObjectsBy($query, $order));
	}

	private function calculateQueryParts(int $ship_coordinate, int $mapfield_coordinate): Map<string, mixed> {
		$result = Map{};	
		if ($mapfield_coordinate > $ship_coordinate) {
			$result['order'] = 'DESC';
			$result['start'] = $ship_coordinate;
			$result['end'] = $mapfield_coordinate;
		} else {
			$result['order'] = 'ASC';
			$result['start'] = $mapfield_coordinate;
			$result['end'] = $ship_coordinate;
		}
		return $result;
	}
}
