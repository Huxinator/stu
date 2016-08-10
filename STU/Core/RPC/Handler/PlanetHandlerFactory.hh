<?hh // strict
namespace STU\Core\RPC\Handler;

use STU\Model\PlanetTableInterface;

final class PlanetHandlerFactory {

	public function __construct(private PlanetTableInterface $planet_table): void {
	}

	public function createPlanetListHandler(): Planet\PlanetListHandler {
		return new Planet\PlanetListHandler($this->planet_table);
	}
}
