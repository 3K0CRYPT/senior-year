document.addEventListener('DOMContentLoaded', () => {
    const canvas = document.getElementById("canvas");
    const ctx = canvas.getContext('2d');
    canvas.resize = function() {
        canvas.height = window.innerHeight;
        canvas.width = window.innerWidth;
        ctx.fillRect(0, 0, canvas.width, canvas.height);
    }
    canvas.resize();
    window.addEventListener('resize', canvas.resize, false);
})