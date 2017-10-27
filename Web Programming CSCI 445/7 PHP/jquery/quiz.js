var _qs = {
    "Q1": {
        q: "The first Pokemon that Ash caught himself was a Caterpie.",
        d: "First pokemon",
        a: true
    },
    "Q2": {
        q: "The first legendary pokemon Ash encounters is Mewtwo.",
        d: "First legendary",
        a: false
    },
    "Q3": {
        q: "Ghost is super-effective against Psychic.",
        d: "Type-effectiveness",
        a: true
    },
    "Q4": {
        q: "The Fairy-type was a horrible addition that has non-intuitive type advantages.",
        d: "Fairy-type",
        a: true
    },
    "Q5": {
        q: "You want to be the very best.",
        d: "Like no one ever was",
        a: true
    },

}

var _bool, correct = 0;

$(document).ready(function() {
    var Q = $("#Q").text('Select a question from below!');
    var answered = $("#answered").html('');
    var answer = $("#answer").text("Check answer");
    var T = $("#T")
    var F = $("#F")

    T.click(() => {
        _bool = true;
        F[0].checked = false;
    })
    F.click(() => {
        _bool = false;
        T[0].checked = false;
    })

    for (var n of Object.keys(_qs)) {
        var _b = document.createElement("button")
        _b = $(_b)
        _b.attr('id', n)
        _b.text(_qs[n].d)
        _b.addClass("quest")
        $('#questions').append(_b)
            // $('#'+n).text(_qs[n].d)
    }

    answer.click(() => {
        if (!$('.current').length) window.alert("Pick a question first!")
        else if (!T[0].checked && !F[0].checked) window.alert("You must pick an answer!")
        else {
            var _q = $('.current')
            if (_bool == _qs[_q[0].id].a) {
                window.alert("Correct!");
                correct++
            } else window.alert("Wrong, sorry!")

            _q.fadeOut();
            answered.append("<div>" + _qs[_q[0].id].d + "</div>")
            T[0].checked = false;
            F[0].checked = false;
            _q.removeClass("current")
            _q.addClass("answered")
            if ($(".answered").length == Object.keys(_qs).length) {
                Q.text("You finished the quiz, your score: ");
                var _d = document.createElement("div");
                _d = $(_d)
                _d.text(correct + "/" + Object.keys(_qs).length + "(Double click me!)")
                _d.addClass("gameover");
                _d.dblclick(() => {
                    _d.animate({ height: '300px', opacity: '0.4' }, "slow");
                    _d.animate({ width: '300px', opacity: '0.8' }, "slow");
                    _d.animate({ height: '0', opacity: '0.8' }, "slow");
                    _d.fadeOut()
                })
                Q.append(_d)
                T.fadeOut()
                F.fadeOut()
                answer.fadeOut()
                $('#buttons').fadeOut()
            } else Q.text('Select a question from below!');
        }
    })

    $(".quest").hover(
        (e) => {
            $(e.target).css("background-color", "red");
            if (!$('.current').length) Q.text('Click to see the question!')
        }, (e) => {
            $(e.target).css("background-color", "initial")
            if (!$('.current').length) Q.text(' ')
        }).click((e) => {
        if ($('.current').length) window.alert("Please finish answering the current question.")
        else {
            var _q = $(e.target)
            _q.addClass("current")
            Q.text(_qs[_q[0].id].q)
        }
    })
})