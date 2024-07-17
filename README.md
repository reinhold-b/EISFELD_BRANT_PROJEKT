# KITTI-Game Albert Eisfeld, Reinhold Brant

## Starten

Um das Spiel auf einer Windows Machine auszuführen, muss die CMakeLists.txt in der root des Projekts liegen 
(ist von Haus aus der Fall) und die CMake Tools Extension von Microsoft und die CMake Extension von twxs installiert sein.

Nun VSCode einmal neu starten und unten links in der Toolbar das Projekt builden und ausführen.

Das Projekt enthält außerdem Unit-Tests, die mit Google Test realisiert werden. Um diese auszuführen, muss in der Toolbar unten links auf das Reagenzglassymbol geklickt werden.

## Implementierung

### Frame
`
Der Hauptaufbau des Projekts basiert auf der `Frame` Klasse, die, wie der Name verrät, eine Art "Bilderrahmen" für die
einzelnen Bilder darstellt. Die `Frame` Klasse besitzt alle nötigen Attribute, die das Bild beschreiben, wie dessen Pfad
und die Bounding Boxes, die darauf angezeigt werden. Für weitere Infos zum Frame kann das UML Diagramm "uml1.png" konsultiert werden.
`
Da zwei Spielmodi verfügbar sind, sind zwei weitere Klassen von `Frame` abgeleitet: `SingleGameFrame` und `MultiGameFrame`.

### SingleGameFrame

Beim SingleGame wird nur eine Box angezeigt, die so schnell wie möglich angeklickt werden muss. 
Der ‘SingleGameFrame‘ unsterscheidet sich dabei nur in der `show()` Methode, was folgend im Vergleich erläutert wird.

### MultiGameFrame

Im MultiGame werden mehrere BBs gleichzeitig angezeigt. Nach einer zufälligen Zeit muss eine angeklickt werden.

Die `show()` Methode wird auf jedes Frame in der `main()` aufgerufen:
```cpp
    for (int i = 0; i < numImages; i++)
    {
        frame = fac.take(gamemode);
        (*frame).show();
        times.push_back(frame->result);
    }
```
Sie ist für das `SingleGameFrame` und das `MultiGameFrame` aus `Frame` polymorph und unterscheidet sich unter anderem dadurch, dass sie für das eine z.B. Verzögerungen vor dem Anzeigen der zu drückenden Box realisiert und beim anderen schlichtweg nur das Frame (Bild) selbst anzeigt.

### FrameFactory

Die FrameFactory stellt in der `main()` Frames je nach Spielmodus zur Verfügung. Sie wählt zufällig Bilder aus der ausgewählten Sequenz aus und konstruiiert das Frame mit den dazugehörigen Attributen wie Dateipfad und Labels.
