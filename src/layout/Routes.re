[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  switch (url.path) {
  | ["articles", id] => <Article id />
  | _ => <ArticlesList />
  };
};