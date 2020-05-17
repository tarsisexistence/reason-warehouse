[@react.component]
let make = (~article: Types.article) => {
  let dateCreated = Js.Date.fromString(article.date_created);
  let getMonthName = monthOrder =>
    switch (monthOrder) {
    | 0 => "January"
    | 1 => "February"
    | 2 => "March"
    | 3 => "April"
    | 4 => "May"
    | 5 => "June"
    | 6 => "July"
    | 7 => "August"
    | 8 => "September"
    | 9 => "October"
    | 10 => "November"
    | 11 => "December"
    | _ => "Never"
    };

  let month = dateCreated |> Js.Date.getMonth |> int_of_float |> getMonthName;
  let day = dateCreated |> Js.Date.getDate;
  let year = dateCreated |> Js.Date.getFullYear;

  <article
    style={ReactDOMRe.Style.make(~display="block", ~padding="30px 0", ())}>
    <h3
      style={ReactDOMRe.Style.make(
        ~fontSize="1.75rem",
        ~marginBottom="0.4375rem",
        (),
      )}>
      <a
        style={ReactDOMRe.Style.make(
          ~boxShadow="none",
          ~marginBottom="0.4375rem",
          (),
        )}
        href={article.id}>
        {React.string(article.title)}
      </a>
    </h3>
    <small style={ReactDOMRe.Style.make(~fontSize="80%", ())}>
      {React.string({j|$month $day, $year | 5 min read|j})}
    </small>
    <p> {React.string("Let clean code guide you. Then let it go")} </p>
  </article>;
};