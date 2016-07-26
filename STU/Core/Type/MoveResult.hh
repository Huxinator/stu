<?hh // strict
namespace STU\Core\Type;

use STU\Model\ShipTableInterface;

class MoveResult implements \JsonSerializable {

	private ?string $result_message;

	public function __construct(private ShipTableInterface $ship): void{
	}

	public function jsonSerialize(): array<string, mixed> {
		return [
			'ship' => new Ship($this->ship),
			'message' => $this->result_message
		];
	}

	public function setResultMessage(string $message): void {
		$this->result_message = $message;
	}
}
