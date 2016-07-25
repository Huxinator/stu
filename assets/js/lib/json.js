var json = {

	session_error_code: -42,

	setup: function() {
		$.jsonRPC.setup({
			endPoint: '/rpc.hh'
		});
	},

	request: function(method, parameters, onsuccess, onfailure) {
		if (!onfailure) {
			onfailure = function(result) {
				console.log(result);
			};
		}
		$.jsonRPC.request(method, {
			params: parameters,
			success: onsuccess,
			error: function(result) {
				if (result.error && result.error.code == json.session_error_code) {
					displayLogin();
				} else {
					onfailure(result);
				}
			}
		});	
	},

}
