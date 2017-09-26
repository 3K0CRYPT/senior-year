document.addEventListener('DOMContentLoaded', () => {
    const canvas = document.getElementById("canvas");
    const ctx = canvas.getContext('2d');
    const img = document.getElementsByTagName("img")[0]
    canvas.resize = function() {
        canvas.width = window.innerWidth;
        wmax = (canvas.width / 2) - img.width / 2
        hmax = (canvas.height / 2) - img.height / 2
        draw({ keyCode: -1 })
    }
    canvas.resize();
    window.addEventListener('resize', canvas.resize, false);

    var _speed = 5,
        ix = 0,
        iy = 0,
        wmax = 0,
        hmax = 0;

    img.onload = (e) => {
        wmax = (canvas.width / 2) - e.target.width / 2
        hmax = (canvas.height / 2) - e.target.height / 2
    }


    function draw(e) {
        console.log(e.which)
        ctx.save();
        // ctx.clearRect(0, 0, canvas.width, canvas.height);

        ctx.save();
        ctx.globalAlpha = 0.33;
        ctx.globalCompositeOperation = 'destination-out';
        ctx.fillStyle = '#FFF';
        ctx.fillRect(0, 0, canvas.width, canvas.height);
        ctx.restore();

        ctx.translate(canvas.width / 2, canvas.height / 2);
        ctx.translate(-img.width / 2, -img.height / 2)

        switch (e.keyCode) {
            case 38: //up
                iy -= _speed;
                break;
            case 37: //left
                ix -= _speed;
                break;
            case 40: //right
                iy += _speed;
                break;
            case 39: //Down
                ix += _speed;
                break;
            default:
                break;
        }

        iy = Math.min(Math.max(-hmax, iy), hmax)
        ix = Math.min(Math.max(-wmax, ix), wmax)

        ctx.drawImage(img, ix, iy)
        ctx.restore()
    }
    window.onkeydown = draw
})