// This function gets your whole document as its `body` and formats
// it as an article in the style of the IEEE.

#let quote_block(body) = {
  block(
    width: 100%,
    fill: silver,
    inset: 8pt,
    body
  )
}

#let terminal(body) = {
  block(
    width: 100%,
    fill: black,
    inset: 8pt,
    text(white, body)
  )
}

#let style(
  // The paper's title.
  title: "Challenge Title",

  // Challenge ID
  number: (),
  // Author
  author: (),
  // Date
  date: (),
  // Time limit
  time_limit: (),

  // The article's paper size. Also affects the margins.
  paper-size: "a4",

  // The paper's content.
  body
) = {
  // Set document metadata.
  set document(title: title, author: author.name)

  // Set the body font.
  set text(lang: "ja", size: 10pt, font: "Noto Serif CJK JP")

  // Set image size.
  set image(width: 80%)

  // Set table caption upper.
  show figure.where(
    kind: table
  ): set figure.caption(position: top)

  // Configure the page.
  set page(
    paper: paper-size,
    // The margins depend on the paper size.
    margin: if paper-size == "a4" {
      (x: 71.5pt, top: 40.51pt, bottom: 49.51pt)
    } else {
      (
        x: (50pt / 216mm) * 100%,
        top: (55pt / 279mm) * 100%,
        bottom: (64pt / 279mm) * 100%,
      )
    },
    header: align(right, text(8pt)[
      Juggernaut\#002
    ]),
    footer: align(left, text(8pt)[
      $copyright$2024 Norimasa TAKANA
    ]),
    numbering: "1",
  )

  set raw(theme: "../monokai.tmTheme", tab-size: 4)
  show raw: it => block(
    width: 100%,
    fill: rgb("#1d2433"),
    inset: 8pt,
    radius: 5pt,
    text(fill: rgb("#c2cacc"), it)
  )
  show raw.line: it => {
    box(
      width: 100%,
      align(horizon, stack(
        dir: ltr,
        box(
          width: 17pt,
          inset: (x: 7pt),
          align(right, text(white)[
              #it.number
          ]
        )),
        it.body,
      ))
    )
  }

  // Configure equation numbering and spacing.
  set math.equation(numbering: "(1)")
  show math.equation: set block(spacing: 0.65em)

  // Configure lists.
  set enum(indent: 10pt, body-indent: 9pt)
  set list(indent: 10pt, body-indent: 9pt)

  // Configure headings.
  set heading(numbering: "1.")

  // Display the paper's title.
  v(3pt, weak: true)
  figure(
    image("../images/logo.png", width: 75%),
  )
  figure(
    table(
      columns: (15%, 50%),
      stroke: (x: none),
      align: left,
      table.hline(y: 1, start: 0),
      table.vline(x: 1, start: 0),
      [装置名], [#title],
      [装置番号], [#number],
      [作問者], [#author.name],
      [作問日], [#date.display()],
      [制限時間], [#time_limit.display()],
    ),
  )
  v(8.35mm, weak: true)

  // Display the author name
  v(20pt, weak: true)

  set par(justify: true, first-line-indent: 1em)
  show par: set block(spacing: 0.65em)

  // Display the paper's contents.
  body
}

