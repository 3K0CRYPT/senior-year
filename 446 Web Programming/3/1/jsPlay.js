snowInches = 5;

var skiArea = {
    name: "Copper",
    base: 19,
    isOpen: function() { return this.base >= 24 },
    openSoon: function() { return (this.base + snowInches) >= 24 },
    openTomorrow: function(snowInches) { return (this.base + snowInches) >= 24 }
}

document.writeln(skiArea.name)
document.writeln(skiArea.isOpen())
document.writeln(skiArea.isOpen)
document.writeln(snowInches)
document.writeln(skiArea.openSoon())
document.writeln(skiArea.openTomorrow())

var backCountry = function(vertical) {
    document.writeln(vertical);
    avalancheChance = 50;
    var vertical = 800;
    document.writeln(vertical);
    snowInches = 20;
}

try { document.writeln(avalancheChance) } catch(e) { document.writeln("Couldn't write avalanchChance")}
//It hasn't been declared and hoisted since we haven't called backCountry yet

backCountry();

document.writeln(avalancheChance)
document.writeln(snowInches)