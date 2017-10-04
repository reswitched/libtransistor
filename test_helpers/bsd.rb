require "socket"

server = TCPServer.new(5555)

child = fork do
  exec(ARGV[0], "--load-nro", "build/test/test_bsd.nro", "--enable-sockets")
end

client = server.accept
msg = client.recv(512)
if(msg != "Hello from libtransistor over a socket!\x00") then
  Process.kill("INT", child)
  raise "wrong hello message (got '#{msg}')"
end

client.send("testing recv...\x00", 0)
puts "waiting on eof..."
if(!client.eof) then
  Process.kill("INT", child)
  raise "remote end didn't close socket"
end
puts "eof reached"

client.close
server.close

puts "connecting"
client = TCPSocket.new("127.0.0.1", 4444)
puts "connected"
msg = client.recv(512)
if(msg != "Hello from libtransistor over a socket!\x00") then
  Process.kill("INT", child)
  raise "wrong hello message (got '#{msg}')"
end

client.send("testing recv...\x00", 0)
if(!client.eof) then
  Process.kill("INT", child)
  raise "remote end didn't close socket"
end

Process.wait(child)
exit($?.exitstatus)
