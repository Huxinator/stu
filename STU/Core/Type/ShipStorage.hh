<?hh // strict
namespace STU\Core\Type;

use STU\Model\ShipStorageTableInterface;

final class ShipStorage implements ShipStorageInterface {

	public function __construct(private Vector<ShipStorageTableInterface> $storage): void {
	}

	public function jsonSerialize(): array<int, array<string, int>> {
		$result = [];
		foreach ($this->storage as $item) {
			$result[] = [
				'commodity_id' => $item->getCommodityId(),
				'amount' => $item->getAmount()
			];	
		}	
		return $result;
	}
}
