document.addEventListener('DOMContentLoaded', () => {
    window.alert("Welcome to Concentration!\nClick on cards to turn them over. You can turn over 2 cards per turn to try and find a match. Try to remember all the cards that have been turned over!\nThe player with the most matches at the end wins.")

    //SLeep function from: https://stackoverflow.com/questions/951021/what-is-the-javascript-version-of-sleep
    function sleep(ms) { return new Promise(resolve => setTimeout(resolve, ms)); }

    const matches = [document.getElementById("p1"), document.getElementById("p2")];
    const headers = [document.getElementById("p1header"), document.getElementById("p2header")];
    const board = document.getElementById("board")

    var playerOneTurn = true; //This is used to determine who is rewarded for successful match.
    var secondCardSelection = false; //This is used to check if it's the second card selection.
    var lastSelected = {}; //Stores the last selected card ID (to check match)


    ///////////////////////////////////////////////////////////////Expects 13 images numberered 0-12 in the same folder!
    //Populate the deck
    const cards = 13
    const shuffle = true; // Set false to not shuffle
    var cardPool = {}; //For shuffling

    //Place all possible card ID's
    for (var im = 0; im < cards * 2; im++) {
        var index = parseInt(im / 2);
        cardPool[index] = 1;
    }

    //I did not get this shuffling algorithm from anywhere! 
    //Get random index from the pool, delete if it has been exhausted.
    //          This is just selection without replacement!
    while (Object.keys(cardPool).length) {
        var index = shuffle ? parseInt(Math.floor(Object.keys(cardPool).length * Math.random())) : 0;
        var suit = Object.keys(cardPool)[index];
        var suitID = cardPool[suit]--;
        var card = document.createElement("div")
        card.className = "covered card"
        card.id = `${suit},${suitID}` //e.g. third card id="1,0"
        card.addEventListener("click", checkMove, false)
        board.appendChild(card)

        if (cardPool[suit] < 0) delete cardPool[suit];
    }


    var highlightPlayer;
    (highlightPlayer = function() { //Highlight's the turn of the current player
        headers[playerOneTurn ? 0 : 1].style.border = "1vh dashed #FFFF00"
        headers[playerOneTurn ? 1 : 0].style.border = "none"
    })()

    function checkMove(e) {
        //Turn the card over
        e.target.className = "card";
        e.target.style.backgroundImage = `url("./${e.target.id.split(',')[0]}.png")`

        if (!secondCardSelection) {
            lastSelected = e.target;
            secondCardSelection = true;
            lastSelected.style.border = "0.5vh solid #FFFF00";
        } else {
            lastSelected.style.border = "none";
            if (e.target.id == lastSelected.id) return
            else if (e.target.id.split(',')[0] === lastSelected.id.split(',')[0]) {
                matches[playerOneTurn ? 0 : 1].appendChild(e.target)
                matches[playerOneTurn ? 0 : 1].appendChild(lastSelected)
                e.target.removeEventListener("click", checkMove)
                lastSelected.removeEventListener("click", checkMove)
            } else {
                var preserve = [e.target, lastSelected];
                (async function() {
                    await sleep(500);
                    for (var e of preserve) {

                        /* FOR GRADER: comment out these 2 lines 
                        - these are the lines that turn cards back over if no match
                        - when commented out, the cards are always visible
                        /* FOR PLAYING: reverse the commenting of these 2 lines */
                        e.className = "covered card";
                        e.style.backgroundImage = "";
                        /*//////////////////////////////////////////////////////////////////*/

                    }
                })()
            }
            playerOneTurn = !playerOneTurn
            secondCardSelection = false;
            lastSelected = {};
            highlightPlayer()
        }

        if (board.childNodes.length <= 1) {
            var count = [
                matches[0].childNodes.length - 1,
                matches[1].childNodes.length - 1
            ]
            if (count[0] == count[1]) window.alert(`It was a draw! Both players got ${Math.ceil((count[0])/2)} matches!`)
            else {
                var winner = count[0] < count[1]
                window.alert(`Congratulations to Player ${winner+1}! They got ${count[winner ? 1 : 0]/2} matches!`)
            }
        }
    }
})