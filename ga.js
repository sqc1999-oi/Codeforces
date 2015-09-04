document.cookie="myVal=123"
var s = document.cookie.split(";");
for (var i = 0; i < s.length; i++) {
	var ss = s[i].split("=");
	if (ss[0] == "myVal" && ss[1] == "123") {
		(function (i, s, o, g, r, a, m) {
			i['GoogleAnalyticsObject'] = r;
			i[r] = i[r] || function () {
					(i[r].q = i[r].q || []).push(arguments)
				}, i[r].l = 1 * new Date();
			a = s.createElement(o),
				m = s.getElementsByTagName(o)[0];
			a.async = 1;
			a.src = g;
			m.parentNode.insertBefore(a, m)
		})(window, document, 'script', '//www.google-analytics.com/analytics.js', 'ga');
		
		ga('create', 'UA-66641508-1', 'auto');
		ga('send', 'pageview');
		var _hmt = _hmt || [];
		(function () {
			var hm = document.createElement("script");
			hm.src = "//hm.baidu.com/hm.js?e8ad2ee6ad931ae0751a3a660ea2ac43";
			var s = document.getElementsByTagName("script")[0];
			s.parentNode.insertBefore(hm, s);
		})();
	}
}