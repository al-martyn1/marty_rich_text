#! Мой жирный текст формат :)

Структура классов инспирирована форматом FB2, но не зависит от него.
С некоторыми упрощениями, полагаю, к этому формату можно привести и FB3 и Epub,
при необходимости (или ещё какой-то формат ебуков), и/или как-то минимально дополнить,
при появлении каких-то специфических фишек.

Парсер FB2 не свой, используется pugixml.

Базовые стили strong/emphasis/code/teletype/pre/sub/sup/bold/italic/strikeout/underlined
работают внутри параграфа (struct Para) и не иерархичны: так, 
 <emphasis><emphasis>Double deep emphasis</emphasis></emphasis>
 и 
 <emphasis>Single deep emphasis</emphasis>
не будут ничем отличаться.

Это не так клёво, как у взрослых, но достаточно клёво для отображения FB2 и маркдауна,
более, чем достаточно для моего текущего проекта, и вполне достаточно для 
90% других проектов.

Помимо текущего проекта, для которого всё затевалось, тут очевидно выпочковываются 
возможности запилить:
  FB2 Reader  - тут уже практически всё готово
  MD Viewer   - тут надо запилить парсер маркдауна, возможно с поддержкой плагинов

Иерархические секции FB2 преобразовываются в единый список секций, у которых
есть атрибут-индикатор вложенности.

Нужно ещё сделать:
  1) Максимально плоский список простых структур типа Para, но уже по/раз-меченных своим 
     конкретным стилем, чтобы запилить шустрый рендерер всего этого
  2) что-то типа css на говне, какой-то JSON, может быть, чтобы раздавать стили при генерации п.1
  3) Собсно рендерер уже расжеванных и размеченных данных



FB2 формат в коментариях - http://www.fictionbook.org/index.php/FictionBook_2.0_Schema_-_%D0%BA%D0%BE%D0%BC%D0%BC%D0%B5%D0%BD%D1%82%D0%B0%D1%80%D0%B8%D0%B8


Отжимка FB2:

FictionBook - root tag
  description
  body
  binary


description
  title-info
  document-info
  publish-info


title-info
  genre - может быть несколько, в каждом тэге - один жанр
  author
    first-name
    middle-name - необязательно
    last-name
  book-title - заголовок книги
  lang - язык

document-info - информация об XML-документе, его создателе, софте, и тп - не интересует

publish-info
  publisher - информация об издателе. В некоторых книгах есть в начале ненужная секция 
              с инфой об издателе, её можно отсекать используя данное поле.

history - История изменении данного FB2 документа. Не нужен.
  Subelements: 
  Dependant  : document-info - 0..1 (один, опционально).


body - может быть несколько, основной текст только в первом.
<body name="notes">


section - Секция, основной структурный блок книги. Не содержит собственно текста.
  Subelements: Должен содержать последовательность элементов в таком порядке:
               1 <title> - 0..1 (опционально);
               2 <epigraph> - 0..n (любое число, опционально);
               3 <image> - 0..1 (опционально);
               4 <annotation> - 0..1 (опционально);
               5 Один из вариантов,
                 1 либо вложенные секции:
                   <section> - (любое число, обязательно);
                 2 либо произвольный набор (в произвольном количестве) из следующих элементов:
                   p, image, poem, subtitle, cite, empty-line, table
  Dependant  : body, section

title - Название книги, главы, стихотворения. Не содержит собственно текста.
  Subelements: p, empty-line
  Dependant  : body, section, poem, stanza

subtitle - !!! не содержит подразделов, только оформление
  Subelements: strong, emphasis, style, a, strikethrough, sub, sup, code, image
  Dependant  : section, cite, stanza, title-info, src-title-info, history

  Аналогичен тэгу "p" - para

image
  Subelements: Нет подчиненных элементов, обычно нет закрывающего тэга (пустой элемент).
  Dependant  : body, section, coverpage, p, v, subtitle, th, td, text-author

text-author - !!! не содержит подразделов, только оформление
  Subelements: strong, emphasis, style, a, strikethrough, sub, sup, code, image

annotation - может находиться в секции
  Subelements: p, poem, cite, subtitle, empty-line, table
  Dependant  : title-info, src-title-info, section

p - !!! не содержит подразделов, только оформление
  Subelements: strong, emphasis, style, a, strikethrough, sub, sup, code, image
  Dependant  : section, title, epigraph, cite, annotation, history

empty-line
  Subelements: Нет подчиненных элементов, нет закрывающего тэга.
  Dependant  : section, annotation, history, title, epigraph, cite

epigraph
  Subelements: Содержит в перечисленном порядке элементы:
    1 Произвольный набор (в произвольном количестве): p, poem, cite, empty-line
    2 text-author - 0..n (любое число, опционально).
  Dependant  : body, section, poem

poem
  Subelements: Должен содержать последовательность элементов в таком порядке:
    1 <title> 0..1 (опционально) - название;
    2 <epigraph> 0..n (любое число, опционально) - эпиграф;
    3 <stanza> 1..n (любое число, обязательно) - стихотворные строфы;
    4 <text-author> 0..n (любое число, опционально) - автор стиха;
    5 <date> 0..1 (опционально) - дата написания.
  Dependant  : section, cite, epigraph, annotation, history

cite
  Subelements: Содержит в указанном порядке следующие элементы:
    1 Произвольный набор (в произвольном количестве):
      p, subtitle, empty-line, poem, table
    2 text-author - 0..n (любое число, опционально) - подпись, автор цитируемого текста.
  Dependant  : annotation, epigraph, history, section

stanza - Строфа - стихотворная группа строк, отделенная пустым промежутком от остальных строк.
  Subelements: Должен содержать последовательность элементов в таком порядке:
               1 <title> 0..1 (опционально);
               2 <subtitle> 0..1 (опционально);
               3 <v> 1..n (любое число, обязательно).
  Dependant  : poem

v - Строка стихотворения (стих) - !!! не содержит подразделов, только оформление
  Subelements: strong, emphasis, style, a, strikethrough, sub, sup, code, image
  Dependant  : stanza

code - Предназначен для оформления терминов, строк программного кода и подобных фрагментов текста, обычно отображаемых шрифтом фиксированной ширины.
  Subelements: 
  Dependant  : 
  Sample     : <p><code>if (user.loggedIn) {</code></p>
               Но так мало кто делает

  Subelements: 
  Dependant  : 

table
  Атрибуты
    id (опциональный) - Идентификатор (якорь, метка) для ссылок на данный элемент
    style (опциональный) - стиль таблицы
  Подчиненные элементы
    Должен содержать элементы:
    <tr> 1..n (любое число, один обязательно).

tr
  Атрибуты
    align (опциональный) - вырабнивание "left"/"right"/"center"
  Подчиненные элементы
    Произвольный набор (в произвольном количестве) из следующих элементов:
    <th>;
    <td>.

th
  Атрибуты
    id (опциональный);
    style (опциональный);
    colspan (опциональный);
    rowspan (опциональный);
    align (опциональный) - "left"/"right"/"center"
    valign (опциональный) - "top"/"middle"/"bottom"
    xml:lang (опциональный) - язык.
  Подчиненные элементы
    Аналогично <p>

td
  Атрибуты
    id (опциональный);
    style (опциональный);
    colspan (опциональный);
    rowspan (опциональный);
    align (опциональный) - "left"/"right"/"center"
    valign (опциональный) - "top"/"middle"/"bottom"
    xml:lang (опциональный) - язык.
  Подчиненные элементы
    Аналогично <p>

th/td - аналогичны <p>, но есть доп атрибуты
    В ячейке таблицы может быть несколько <p>, но в FB2 вроде th/td и есть как один <p>

sub, sup, history - удаляем.
a - удаляем, если текст в []

table - удаляем, не умеем с ними работать

Элементы нижнего уровня, без подразделов, только оформление.
p, v, subtitle, empty-line, text-author


strong
emphasis
style
a
strikethrough
sub
sup
code
image

   <empty-line/>
   <p>Some text <image l:href="#img_3"/> more text</p>
   <empty-line/>
   <p><strong>Рис. 1.1.</strong> <emphasis>Взаимоотношения между различными стандартами UNIX и C</emphasis></p>
   <p>В 2008 году  <emphasis>The New York Times</emphasis>, проделал</p>
