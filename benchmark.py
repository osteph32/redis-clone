import socket
import time

HOST = "localhost"
PORT = 6379
REQUESTS = 1000

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((HOST, PORT))

start = time.time()

for i in range(REQUESTS):
    cmd = f"SET key{i} value{i}\n"
    client.send(cmd.encode())
    client.recv(1024)

end = time.time()

elapsed = end - start
rps = REQUESTS / elapsed

print(f"Requests: {REQUESTS}")
print(f"Elapsed: {elapsed:.4f}s")
print(f"Requests/sec: {rps:.2f}")

client.close()