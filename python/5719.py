import sys, heapq
input = sys.stdin.readline

INF = int(1e9) + 7

def Dijkstra(adj, dist, st, flag = 0):
    dist[st] = 0; PQ = [(dist[st], st)]
    while PQ:
        cdist, cur = heapq.heappop(PQ)
        if dist[cur] != cdist: continue
        for nxt, cost in adj[cur]:
            if flag and dist1[cur] + cost + dist2[nxt] == dist1[en]: continue
            if dist[nxt] > cdist + cost:
                dist[nxt] = cdist + cost
                heapq.heappush(PQ, (dist[nxt], nxt))

while 1:
    n, m = map(int, input().split())
    if n == 0 and m == 0: break
    st, en = map(int, input().split())

    adj = [[] for _ in range(n)]
    rev = [[] for _ in range(n)]
    dist1, dist2, dist3 = [INF] * n, [INF] * n, [INF] * n

    for _ in range(m):
        a, b, c = map(int, input().split())
        adj[a].append((b, c))
        rev[b].append((a, c))

    Dijkstra(adj, dist1, st)
    Dijkstra(rev, dist2, en)
    Dijkstra(adj, dist3, st, 1)

    print(dist3[en] if dist3[en] != INF else -1)