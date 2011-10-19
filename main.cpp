#include <QtCore/QCoreApplication>
#include "node.h"
#include <QStack>
#include <QHash>
#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QList<QString> nodes;
    nodes << "under" << "socks" << "pants" << "shoes" << "belt"
          << "shirt" << "tie" << "jacket" << "watch";

    Digraph g(nodes);
    g.addEdge("under","shoes");
    g.addEdge("under","pants");
    g.addEdge("socks","shoes");
    g.addEdge("pants","shoes");
    g.addEdge("pants","belt");
    g.addEdge("belt","jacket");
    g.addEdge("shirt","belt");
    g.addEdge("shirt","tie");
    g.addEdge("tie","jacket");
    g.addEdge("jacket","tie");

    QList<QString> nodes2;
    nodes2 << "b" << "c" << "d";

    Digraph g2(nodes2);
    g2.addEdge("a","b");
    g2.addEdge("a","c");
    g2.addEdge("b","c");
    g2.addEdge("d","b");
    g2.addEdge("c","d");

    Toposort topo(g2);
    qDebug() << "Is DAG: "<< topo.isDAG();
    qDebug() << "Has Cycle: "<< topo.hasCycle();
    qDebug() << topo.cycle();

    qDebug() << topo.order();

    return app.exec();
}
