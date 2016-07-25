<?hh
namespace STU\Core\RPC;

use STU\Core\Type\Ship;

class Shiplist extends Base {

	public function getList(): array<int, Ship> {
		$user_id = $this->getSessionManager()->getUserId();

		$shiplist = $this->getDIContainer()->ship->getObjectsBy('user_id='.$user_id);

		$ships = [];
		foreach ($shiplist as $ship) {
			$ships[] = new Ship($ship);
		}
		return $ships;
	}

}
