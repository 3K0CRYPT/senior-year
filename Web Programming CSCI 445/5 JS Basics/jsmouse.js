document.addEventListener('DOMContentLoaded', () => {
    const canvas = document.getElementById("canvas");
    const ctx = canvas.getContext('2d');
    const button = document.getElementsByTagName("button")[0]
    canvas.resize = function() {
        canvas.height = window.innerHeight;
        canvas.width = window.innerWidth;
        // ctx.fillRect(0, 0, canvas.width, canvas.height);
    }
    canvas.resize();
    window.addEventListener('resize', canvas.resize, false);
    
    var _bool = true;

    function drawSmiley() {
        var _min = Math.min(canvas.width, canvas.height)

        ctx.save();
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        ctx.translate(canvas.width / 2, canvas.height / 2);

        //head
        ctx.beginPath();
        var _radius = _min / 2.5 + (50 - (Math.random() * 100))
        ctx.arc(0, 0, _radius, 0, 2 * Math.PI);

        var grad = ctx.createRadialGradient(0, 0, 0, 0, 0, _radius);
        grad.addColorStop(1, "rgba(0,0,0,0.5");
        grad.addColorStop(0.85, _bool ? "yellow" : "orange");

        ctx.fillStyle = grad
        ctx.fill();
        ctx.closePath();

        //Mouth
        ctx.beginPath();
        var _radius2 =_radius - (80- (Math.random() * 50)) 
        ctx.arc(0, 0, _radius2, 0, Math.PI);
        
        grad = ctx.createRadialGradient(0, 0, 0, 0, 0, _radius2);
        grad.addColorStop(0.8, "black");
        grad.addColorStop(1, "rgba(255,255,255,0.1");
        
        ctx.fillStyle = grad;
        ctx.fill();
        ctx.closePath();

        //Eyes
        ctx.beginPath();
        ctx.arc(-_min / 10 - (Math.random() * _min / 20), -_min / 10 + (50 - (Math.random() * 100)), _min / 25 + (5 - (Math.random() * 10)), 0, 2 * Math.PI);
        ctx.arc(_min / 10 + (Math.random() * _min / 20), -_min / 10 + (50 - (Math.random() * 100)), _min / 25 + (5 - (Math.random() * 10)), 0, 2 * Math.PI);
        ctx.fillStyle = "black";
        ctx.fill();
        ctx.closePath();

        ctx.restore();
        _bool = !_bool;
        
        button.innerHTML = "Draw " + (_bool ? "yellow" : "orange") + " smiley!";
        
    }
     button.onclick = drawSmiley;
})