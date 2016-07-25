<?hh
namespace STU\Core\RPC;

class Maindesk extends Base {

	public function getCommonData(): array<string, mixed> {
		$current_user = $this->getSessionManager()->getCurrentUser();

		$data = array(
			'username' => $current_user->getName(),
			'faction_id' => 1
		);

		return $data;
	}
}
