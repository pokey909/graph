#ifndef NODE_H
#define NODE_H

#include <QString>
#include <QList>
#include <QSet>
#include <QHash>

class Digraph
{
public:
    Digraph(const QList<QString> vertices) : m_verts(vertices)
    {
    }

    int numVertices() const { return m_verts.size(); }
    int numEdges() const { return m_adj.values().size(); }
    const QList<QString>& vertices() const { return m_verts; }
    QSet<QString> adj(const QString &v) const { return m_adj[v]; }

    void addEdge(const QString &v, const QString &w) { m_adj[v] << w; }

    Digraph reverse()   // might be useful for uninstalling
    {
        Digraph g(m_verts);
        foreach (const QString v, m_verts)
            foreach (const QString w, adj(v))
                g.addEdge(w,v);
        return g;
    }

private:
    QHash<QString, QSet<QString> > m_adj;   // adjacency list
    QList<QString> m_verts;
};

class Toposort {
public:
    Toposort(const Digraph &g)
    {
        foreach (const QString v, g.vertices())
            if (!m_marked.contains(v))
                dfs(g, v);
    }

    void dfs(const Digraph &g, QString v)
    {
        m_onStack.insert(v);
        m_marked.insert(v);
        foreach (const QString w, g.adj(v).values()) {
            if (hasCycle())
                return;

            if (!m_marked.contains(w)) {
                m_edgeTo[w] = v;
                dfs(g, w);
            } else if (m_onStack.contains(w)) {
                m_cycle.clear();
                for (QString x = v; x != w; x = m_edgeTo[x])
                    m_cycle.prepend(x);
                m_cycle.prepend(w);
                m_cycle.prepend(v);
            }
        }
        if (hasCycle())
            m_revPost.clear();
        else
            m_revPost.prepend(v);
        m_onStack.remove(v);
    }

    bool hasCycle() const { return !m_cycle.isEmpty(); }
    QList<QString> cycle() const { return m_cycle; }
    bool isDAG() const { return !m_revPost.isEmpty(); }
    QList<QString> order() const { return m_revPost; }


private:
    QSet<QString> m_marked;
    QHash<QString, QString> m_edgeTo;
    QList<QString> m_cycle;
    QSet<QString> m_onStack;
    QList<QString> m_revPost;  // reverse postorder
};

#endif // NODE_H
