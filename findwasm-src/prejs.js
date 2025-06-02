var Module = {
	"print": s => {
		const p = document.createElement("p");
		p.innerText = s;
		document.getElementById("o").append(p);
	}
}
