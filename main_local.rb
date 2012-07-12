# encoding: utf-8

require "hpricot"
require "open-uri"
require "mechanize"
require 'time'

require 'rubygems'
require 'mechanize'
require 'sqlite3'

class Bet

  attr_accessor :id, :name, :type, :b_sum, :w_sum, :coef, :result

  def initialize(time, name, type, b_sum, w_sum, coef, result)
    @id = set_id(time).to_i
    @name = name.to_s
    @type = type.to_s
    @b_sum = b_sum
    @w_sum = w_sum
    @coef = coef
    @result = result
  end

  def set_id(time)
    Time.parse(time).to_i
  end

end

def create_db(path)
  db = SQLite3::Database.new(path)
       db.execute <<SQL

         CREATE TABLE bets (
           id INTEGER PRIMARY KEY,
           bet_name VARCHAR(255),
           bet_type VARCHAR(255),
           bet_sum  VARCHAR(255),
           win_sum  VARCHAR(255),
           coef     VARCHAR(255),
           result   VARCHAR(255)
         );
SQL
  db
end

a = Mechanize.new { |agent|
  agent.user_agent_alias = 'Mac Safari'
}



a.get("file://" + "#{Dir.pwd}" + "/output.html") do |page|

  $bets_html = []

  page.search('//div[@class="BetMoreWindow"]').each  do |bet|
    $bets_html.push(bet)
  end

  #puts bets[0]
  #.each { |b| puts b }
end

$bets_html.delete_at(-1)

bets = []

$bets_html.each do |b|
  time = b.css('span.BetDate').text
  name = b.css('span.SportName').text + b.css('span.LeagueName').text
  type = b.css('span.BetType').text
  b_sum = b.css('span.BetValue').text
  w_sum = b.css('span.BetPrize').text
  coef = b.css('span.BetOddSum').text
  result = b.css('span.BetResult').text


  bets.push(Bet.new(time, name, type, b_sum, w_sum, coef, result))
end


if (File.exist?("test.db")) then
  db = SQLite3::Database.open("test.db")
else
  db = create_db("test.db")
end

# try catch here

begin
  bets.each do |bet|
    begin
    puts bet.inspect
    db.execute( "insert into bets (id, bet_name, bet_type, bet_sum, win_sum, coef, result)
  values (#{bet.id}, '#{bet.name}', '#{bet.type}', '#{bet.b_sum}', '#{bet.w_sum}', '#{bet.coef}', '#{bet.result}');")
    rescue Exception => err
      puts err.inspect + " epta"
    end
  end
end



