<?hh // strict
namespace STU\Core\RPC\Handler\Planet;

use STU\Model\PlanetTableInterface;
use STU\Core\Type\PlanetListItemInterface;
use STU\Core\Type\PlanetListItem;

final class PlanetListHandler {

	public function __construct(private PlanetTableInterface $planet_table): void {
	}

	public function handle(int $user_id): Vector<PlanetListItemInterface> {
		$result = Vector{};	
		$planet_list = $this->planet_table->getObjectsBy(
			sprintf('user_id = %d', $user_id)
		);
		foreach ($planet_list as $planet) {
			$result->add(new PlanetListItem($planet));
		}
		return $result;
	}
}
