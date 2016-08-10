<?hh // strict
namespace STU\Core\RPC;

use STU\DI\DIContainer;
use STU\Core\Type\PlanetListItemInterface;

final class Planetlist extends Base {

	public function getList(): Vector<PlanetListItemInterface> {
		$user_id = $this->getSessionManager()->getUserId();

		return $this->getDIContainer()->core_rpc_handler_planet_handler_factory
			->createPlanetListHandler()
			->handle($user_id);
	}
}
