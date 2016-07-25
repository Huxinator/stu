<?hh
namespace STU\Core\Type;

use STU\Model\ShipTableInterface;

class MoveResult implements \JsonSerializable {

	private ?string $result_message;

	public function __construct(private ShipTableInterface $ship): void{
	}

	public function jsonSerialize(): \stdClass {
		$result = new \stdClass();
		$result->ship = new Ship($this->ship);
		$result->message = $this->result_message;
		return $result;	
	}

	public function setResultMessage(string $message): void {
		$this->result_message = $message;
	}

}
